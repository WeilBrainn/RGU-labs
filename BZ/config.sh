#!/bin/bash

# Global Variables
CONFIG_FILE="./configure_file"
DEFAULT_CATALOG="./"
CERTIFICATE_FILE="certificate"

# Function to read user input
read_input() {
    local prompt="$1"
    local variable_name="$2"
    echo "$prompt"
    read "$variable_name"
}

# Create configuration file
setup_configuration() {
    read_input "Enter path" CATALOG
    CATALOG=${CATALOG:-$DEFAULT_CATALOG}

    read_input "Enter path for temp files" FILE_PATH

    echo "$FILE_PATH" > "$CONFIG_FILE"
    echo "$CATALOG" >> "$CONFIG_FILE"
    echo_message "Configuration file created at $CONFIG_FILE"
}

# Create certificate
create_certificate() {
    local target_file="$1/$CERTIFICATE_FILE"
    touch "$target_file"

    read_input "Name:" NAME
    read_input "Surname:" SURNAME
    read_input "Last Name:" PATRONYMIC
    read_input "Email:" EMAIL
    read_input "Phone Number:" PHONE_NUMBER

    {
        echo "name=$NAME"
        echo "surname=$SURNAME"
        echo "patronymic=$PATRONYMIC"
        echo "email=$EMAIL"
        echo "phone_number=$PHONE_NUMBER"
        date
    } >> "$target_file"

    echo_message "Certificate created at $target_file"
}

# Utility function for messages
echo_message() {
    echo -e "\033[32m$1\033[0m"
}

echo_error() {
    echo -e "\033[31m$1\033[0m" >&2
}

# Main Execution
setup_configuration

if [ -z "$CATALOG" ]; then
    create_certificate "./"
else
    create_certificate "$CATALOG"
fi