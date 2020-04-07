# Usage

## Download & install Go

### Windows & Mac OS

Download the OS specific installer from the [golang downloads page](https://golang.org/dl/) and run it.



### Linux (untested)

#### Debian

1. Update your apt-repo definitions ```sudo apt-get update```

2. Downlaod the go binary ```wget https://dl.google.com/go/go1.13.3.linux-amd64.tar.gz``` or download from the [golang downloads page](https://golang.org/dl/).

3. Extract the tarball and move the result to your user bin folder
   ```
   sudo tar -xvf go1.13.3.linux-amd64.tar.gz
   sudo mv go /usr/local
   ```
   
4. Setup your environment variables

   ```
   export GOROOT=/usr/local/go
   ```
   Create a folder where you want to run your go programs from (in this case I will create a folder on the desktop called development)
   
   ```
   mkdir ~/Desktop/development
   export GOPATH=~/Desktop/development
   export PATH=$GOPATH/bin:$GOROOT/bin:$PATH
   ```
   
   
   

## Single time Run

You can run a single time by using ```go run```



## Compile & run

On windows run ```go build -o otp.exe``` and on *nix run ```go build -o otp``` then run the resulting binary with ```otp.exe``` on windows and ```./otp``` on *nix.

