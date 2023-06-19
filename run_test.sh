make build_tests

while getopts "hesc" opt; do
  case $opt in
    h)
      echo "Help option: -h" >&2
      echo "Run engine test: -e" >&2
      ;;
    e)
      ./bin/test_engine.out
      ;;
    s)
      # ./bin/test_server.out
      ;;
    c)
      # ./bin/test_client.out
      ;;
    \?)
      echo "Use help option: -h" >&2
      ;;
  esac
done
