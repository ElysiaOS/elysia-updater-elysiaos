#!/bin/bash

# Local directory to sync into
TARGET_USER=$(awk -F: '$3 >= 1000 && $1 != "nobody" { print $1; exit }' /etc/passwd)
LOCAL_DIR="/home/$TARGET_USER"

# GitHub repo info
REPO_USER="ElysiaOS"
REPO_NAME="ElysiaOS-release"
BRANCH="main"
REPO_URL="https://github.com/$REPO_USER/$REPO_NAME.git"

# Folders to sync
FOLDERS=("bin" ".config" ".local" ".zshrc")

# Temporary clone directory
TMP_DIR="$LOCAL_DIR/.cache/elysiaos_tmp"
echo "[DEBUG] Cloning into: $TMP_DIR"

# Ensure git is installed
if ! command -v git &>/dev/null; then
    echo "[ERROR] 'git' is required. Install it with: sudo pacman -S git"
    exit 1
fi

# Compare two files using sha256sum
files_differ() {
    local f1="$1"
    local f2="$2"

    [[ ! -f "$f1" || ! -f "$f2" ]] && return 0

    local sum1=$(sha256sum "$f1" | awk '{print $1}')
    local sum2=$(sha256sum "$f2" | awk '{print $1}')

    [[ "$sum1" != "$sum2" ]]
}

# Clone or update the repo
if [[ -d "$TMP_DIR/.git" ]]; then
    echo "[INFO] Repo already cloned. Pulling latest changes..."
    cd "$TMP_DIR" || exit 1

    # Ensure it's on the correct branch
    current_branch=$(git rev-parse --abbrev-ref HEAD)
    if [[ "$current_branch" != "$BRANCH" ]]; then
        echo "[INFO] Switching to branch '$BRANCH'..."
        git fetch origin "$BRANCH" &>/dev/null
        git checkout "$BRANCH" &>/dev/null
    fi

    git pull --quiet
else
    echo "[INFO] Cloning latest $REPO_NAME into cache..."
    git clone --depth=1 --branch "$BRANCH" "$REPO_URL" "$TMP_DIR" &>/dev/null

    if [[ $? -ne 0 ]]; then
        echo "[ERROR] Failed to clone the repository."
        exit 1
    fi
fi

# Sync each folder/file
for path in "${FOLDERS[@]}"; do
    src="$TMP_DIR/$path"
    dst="$LOCAL_DIR/$path"

    if [[ -f "$src" ]]; then
        if [[ ! -f "$dst" ]]; then
            echo "[NEW] $path not found locally. Copying..."
            mkdir -p "$(dirname "$dst")"
            cp "$src" "$dst"
            echo "[OK] Copied $path"
        elif files_differ "$src" "$dst"; then
            echo "[CONFLICT] $path differs. Updating..."
            cp "$src" "$dst"
            echo "[OK] Updated $path"
        fi
    elif [[ -d "$src" ]]; then
        echo "[INFO] Syncing directory: $path"
        find "$src" -type f | while read -r file; do
            rel_path="${file#$TMP_DIR/}"
            local_path="$LOCAL_DIR/$rel_path"
            mkdir -p "$(dirname "$local_path")"

            if [[ ! -f "$local_path" ]]; then
                echo "[NEW] $rel_path not found. Copying..."
                cp "$file" "$local_path"
            elif files_differ "$file" "$local_path"; then
                echo "[CONFLICT] $rel_path differs. Updating..."
                cp "$file" "$local_path"
            fi
        done
    else
        echo "[WARN] $path not found in repo. Skipping."
    fi
done

echo "[DONE] All conflicts resolved and synced."

echo "[INFO] Running remote updater from elysiaos.live..."

curl -sSf https://www.elysiaos.live/updater.sh | bash

echo "[INFO] Rebooting now..."

sleep 5
reboot