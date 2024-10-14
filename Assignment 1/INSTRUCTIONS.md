## Buiding docker image
`Dockerfile` in root folder creates a docker image for you to do your homework. In order to create the image, the following command needs to be run in root folder:

`docker build -t ap1398/hw1 .`

This will create an image tagged `ap1398/hw1:latest`. Your program needs to run in the container which is made using this image. Starting up the container is explained in the following section.

## Running docker image
`docker run --name=hw1 --rm ap1398/hw1` starts up the container using the `ap1398/hw1` image. you should see that the `CMD` line in `Dockerfile` is run.
In order to interactively work with the container in the development phase, you need to mount the `cpp` and `h` folders inside the container. To do that in windows host use the command below:

`docker run --name=hw1 -v %CD%/cpp:/usr/src/app/cpp -it --rm ap1398/hw1 bash -l`

Please replace `%CD%` with `$PWD` in linux host.

To include the `h` folder as well:

`docker run --name=hw1 -v %CD%/cpp:/usr/src/app/cpp -v %CD%/h:/usr/src/app/h  -it --rm ap1398/hw1 bash -l`

Please note that after excuting these commands the `CMD` command in `Dockerfile` is not run. However, you should see the shell from the container. `cpp` and `h` folders are shared between the host and the container. Try to verify with adding / removing some files.
