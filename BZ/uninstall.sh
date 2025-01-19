#!/bin/bash

# Global Variables
USERNAME="$(whoami)"
INSTALL_DIRECTORY="/usr/bin/$USERNAME"
CONFIG_DIRECTORY="/etc/$USERNAME"
LOG_DIRECTORY="/var/log/$USERNAME"

FILES_TO_DELETE=(
    "/home/$USERNAME/Desktop/start.sh"
    "/home/$USERNAME/Desktop/BZ/in_instruct.pdf"
    "/home/$USERNAME/Desktop/BZ/user_man.pdf"
    "/home/$USERNAME/Desktop/BZ/license.pdf"
    "/home/$USERNAME/Desktop/BZ/sertificate"
)

# Utility Functions
echo_message() { echo -e "\033[32m$1\033[0m"; }
echo_error() { echo -e "\033[31m$1\033[0m" >&2; }

# Delete Directory Function
delete_directory() {
    local dir_path="$1"
    if [ -d "$dir_path" ]; then
        sudo chmod -R +w "$dir_path"
        if sudo rm -rf "$dir_path"; then
            echo_message "Deleted: $dir_path"
        else
            echo_error "Failed to delete: $dir_path"
        fi
    fi
}

# Delete File Function
delete_file() {
    local file_path="$1"
    if [ -f "$file_path" ]; then
        sudo chmod +w "$file_path"
        if sudo rm "$file_path"; then
            echo_message "Deleted: $file_path"
        else
            echo_error "Failed to delete: $file_path"
        fi
    fi
}

# Main Uninstallation Process
echo_message "Starting uninstallation process..."

delete_directory "$INSTALL_DIRECTORY"
delete_directory "$CONFIG_DIRECTORY"
delete_directory "$LOG_DIRECTORY"

for file in "${FILES_TO_DELETE[@]}"; do
    delete_file "$file"
done

echo_message "Uninstallation completed."
