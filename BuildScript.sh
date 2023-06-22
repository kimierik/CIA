
gcc ./src/main.c -o ./build/main -Wall -ggdb -rdynamic &&

case "$1" in
    -r|--run)
        ./build/main
        ;;
    *)
        echo "invalid args"
esac

