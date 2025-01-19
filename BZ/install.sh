#!/bin/bash

# Global Parameters
CERT_FILE=$(head -n 1 /home/max/Desktop/BZ/configure_file)
TEMP_DIR=$(sed -n '2p' /home/max/Desktop/BZ/configure_file)
SYSTEM_FILES_DIRECTORY="$HOME/Desktop/BZ"
CONFIG_FILES_DIRECTORY="$SYSTEM_FILES_DIRECTORY/conf_files"
LOG_DIRECTORY="/var/log/$USER"
EXECUTABLE_PATH="$SYSTEM_FILES_DIRECTORY/output"
SYMLINK_PATH="/usr/bin/$USER"

# Utility Functions
echo_message() { echo -e "\033[32m$1\033[0m"; }
echo_error() { echo -e "\033[31m$1\033[0m" >&2; }

# Generalized File Permission Setter
set_file_permissions() {
    local target_dir=$1
    local file_pattern=$2
    local permissions=$3
    find "$target_dir" -type f -name "$file_pattern" -exec chmod "$permissions" {} \;
}

# Install Certificate
install_certificate() {
    local file_path="$HOME/sertificate"
    [ -e "$file_path" ] || file_path="$SYSTEM_FILES_DIRECTORY/sertificate"
    if [ -e "$file_path" ]; then
        sudo chown root:root "$file_path"
        sudo chmod 0644 "$file_path"
        echo_message "Roots set for $file_path"
    else
        echo_error "Certificate file not found."
        exit 1
    fi
}

# Set Permissions
set_permissions() {
    chmod -R 0755 "$SYSTEM_FILES_DIRECTORY"
    set_file_permissions "$SYSTEM_FILES_DIRECTORY" "*.sh" 0755
    set_file_permissions "$SYSTEM_FILES_DIRECTORY" "*.conf" 0644
    echo_message "Permissions set for system files."
}

# Move Files
move_files() {
    local dest_dir="$HOME/$USER"
    mkdir -p "$dest_dir"
    cp -r "$SYSTEM_FILES_DIRECTORY"/* "$dest_dir/"
    echo_message "Files moved to user directory: $dest_dir"
}

# Configure Files
configure_files() {
    local config_dest_dir="/etc/$USER"
    sudo mkdir -p "$config_dest_dir"
    sudo chmod 755 "$config_dest_dir"
    sudo cp -r "$CONFIG_FILES_DIRECTORY"/* "$config_dest_dir/"
    echo_message "Configuration files moved to $config_dest_dir"
}

# Create Log Directory
create_log_directory() {
    sudo mkdir -p "$LOG_DIRECTORY"
    sudo chmod 1777 "$LOG_DIRECTORY"
    [ -d "$LOG_DIRECTORY" ] && echo_message "Log directory created at $LOG_DIRECTORY" || echo_error "Failed to create log directory."
}

# Create Symbolic Link
create_symlink() {
    sudo ln -sf "$EXECUTABLE_PATH" "$SYMLINK_PATH"
    [ -L "$SYMLINK_PATH" ] && echo_message "Symbolic link created at $SYMLINK_PATH" || echo_error "Failed to create symbolic link."
}

# Create Additional Links
create_additional_links() {
    local existing_script_path="$SYSTEM_FILES_DIRECTORY/source/source.sh"
    local new_script_path="$HOME/start.sh"
    cp "$existing_script_path" "$new_script_path" && echo_message "Script installed at $new_script_path" || echo_error "Error installing script."
}

# Main Installation Process
echo_message "Starting installation process..."
install_certificate
set_permissions
move_files
configure_files
create_log_directory
create_symlink
create_additional_links
echo_message "Installation successfully completed."
