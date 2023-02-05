make fclean test

while getopts "he" opt; do
  case $opt in
    h)
      echo "Help option: -h" >&2
      echo "Run engine test: -e" >&2
      ;;
    e)
      ./bin/test_engine.out
      ;;
    \?)
      echo "Use help option: -h" >&2
      ;;
  esac
done
