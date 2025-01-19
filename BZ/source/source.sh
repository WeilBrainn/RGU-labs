#!/bin/bash

# Global Variables
USERNAME="$(whoami)"
C_FILE_PATH="$HOME/Desktop/BZ/test.c"
EXECUTABLE_FILE="$(basename -- "$C_FILE_PATH" .c)"
LOG_DIRECTORY="/var/log/$USERNAME"
LOG_FILE="$LOG_DIRECTORY/user_dialog.log"

LOG_DIALOG=false
SILENT_MODE=false
SHOW_INFO=false
SHOW_CS=false
START_TIME=$(date "+%Y-%m-%d %H:%M:%S")

# Utility Functions
echo_message() { echo -e "\033[32m$1\033[0m"; }
echo_error() { echo -e "\033[31m$1\033[0m" >&2; }
write_log() {
    [ "$SILENT_MODE" = false ] && echo "$1" >> "$LOG_FILE"
}

# Parse Command-Line Arguments
while getopts "cdhis" opt; do
    case $opt in
        c) echo_message "Option -c is selected." ;;
        d) LOG_DIALOG=true ;;
        h) SHOW_CS=true ;;
        i) SHOW_INFO=true ;;
        s) SILENT_MODE=true ;;
        *) echo_error "Invalid option: -$OPTARG"; exit 1 ;;
    esac
done

# Create Log Directory
mkdir -p "$LOG_DIRECTORY"

# Compile C Code
gcc "$C_FILE_PATH" -o "$EXECUTABLE_FILE" || { echo_error "Compilation failed."; exit 1; }

# Show Author and Project Info
if [ "$SHOW_INFO" = true ]; then
    cat << INFO
Author: Egor Adodin
Study Group: ITPM-124
Teacher: Alexey Viktorovich Mokryakov
Department: Engineering and Technology
University: RGU Kosygina
INFO
fi

if [ "$SHOW_CS" = true ]; then
    cat << HELP
-c : Run with your configuration file
-d : Enable log dialog saving
-h : Display help information about CS flags
-i : Show author and project information
-s : Silent mode (no log files will be created)
HELP
fi

write_log "Application started at: $START_TIME"

# Execute Program
run_program() {
    if [ "$LOG_DIALOG" = true ]; then
        { time ./$EXECUTABLE_FILE; } 2>&1 | tee -a "$LOG_FILE"
    else
        { time ./$EXECUTABLE_FILE; } > /dev/null 2>&1
    fi
}

run_program

# Record End Time and Duration
END_TIME=$(date "+%Y-%m-%d %H:%M:%S")
DURATION=$(date -u -d @$(( $(date -u -d "$END_TIME" "+%s") - $(date -u -d "$START_TIME" "+%s") )) "+%H:%M:%S")

write_log "Application ended at: $END_TIME"
write_log "Total duration: $DURATION"
write_log "Exit code: $?"

# Final Message
if [ $? -eq 0 ]; then
    echo_message "Program completed successfully."
    [ "$LOG_DIALOG" = true ] && echo_message "Dialog saved in $LOG_FILE."
else
    echo_error "Program encountered an error."
    [ "$LOG_DIALOG" = true ] && echo_error "Dialog saved in $LOG_FILE."
fi
