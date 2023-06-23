
gcc ./src/main.c -o ./build/main -Wall -ggdb -rdynamic &&

case "$1" in
    -r|--run)
        ./build/main
        ;;
    -t|--test)
        gcc ./src/test.c -o ./build/test -Wall -ggdb -rdynamic &&
        ./build/test

    ;;

    *)
        echo "invalid args"
esac

