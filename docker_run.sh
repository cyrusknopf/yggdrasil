docker build -t yg .
docker run --cpus=8 --memory=8G -v $(pwd):/home/yggdrasil --rm --name yg -it yg /bin/bash
