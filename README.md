# tengwar

Basic C ARM64 compiler


### How to use

To build docker image
````
$docker build -t tengwar .
````

##### To run unittest

###### Windows
````
$docker run -it -v %cd%:/tengwar --rm tengwar
````

###### *nix based
````
$docker run -it -v "$pwd":/tengwar --rm tengwar
````
