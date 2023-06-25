
case "$1" in
    -r|--run)
        gcc ./src/main.c -o ./build/main -Wall -ggdb -rdynamic &&
        ./build/main
        ;;
    -t|--test)
        gcc ./src/test.c -o ./build/test -Wall -ggdb -rdynamic &&
        ./build/test;
        echo "$?"
    ;;

    *)
        echo "invalid args"
esac

