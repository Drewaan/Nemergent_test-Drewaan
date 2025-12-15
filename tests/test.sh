EXEC=./entropy

run_test() {
    description=$1
    shift
    echo ""
    echo "[TEST] $description"
    echo "Command: $EXEC $@"
    $EXEC "$@" >output.txt 2>error.txt
    echo "--- STDOUT ---"
    cat output.txt
    echo "--- STDERR ---"
    cat error.txt
    rm -f output.txt error.txt
    echo "--------------"
}

while true; do
    echo "===== TESTER MENU ====="
    echo "1) No parameters"
    echo "2) Single parameter"
    echo "3) First parameter is not numeric"
    echo "4) Second parameter is not numeric"
    echo "5) Number of threads = 0"
    echo "6) Amount per thread = 0"
    echo "7) Small test (1 thread, 1 number)"
    echo "8) Medium test (10 threads, 10 numbers)"
    echo "9) Large test (100 threads, 100 numbers)"
    echo "0) Exit"
    echo ""
    read -p "Select test: " opc

    case $opc in
        1) run_test "No parameters" ;;
        2) run_test "Single parameter" 2 ;;
        3) run_test "First parameter is not numeric" hola 10 ;;
        4) run_test "Second parameter is not numeric" 15 hola ;;
        5) run_test "Number of threads = 0" 0 4 ;;
        6) run_test "Amount per thread = 0" 4 0 ;;
        7) run_test "Small" 1 1 ;;
        8) run_test "Medium" 10 10 ;;
        9) run_test "Large" 100 100 ;;
        0) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid option"; sleep 1 ;;
    esac

    echo ""
    read -p "Press ENTER to continue..." trash
done
