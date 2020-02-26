# Prerequisites
Please first you need to setup you development environment so you can compile and build the code. 
Look up on [setup](https://docs.microsoft.com/en-us/azure/iot-edge/how-to-vs-code-develop-module) and prepare your Visual studio code.

# Compiling and building
After this clone this project somewhere on your machine. 
Then you need to open the folder in your visual studio code and follow [this](https://github.com/Microsoft/vscode-iot-workbench/blob/master/docs/embedded-linux/embedded-linux-get-started.md) link, but you don't need to create project just do initial config as stated in tutorial.

After you succesfully done the compilling you will get new folder or if you already compiled project existing will only change.

You have two ways to get your script on your Dingo.

1. Using Upload to device feature to upload via SSH (look in tutorial before you have explanation)
2. When you compile the code succesfully you will have the energyManager file inside "yourproject/cmake/energyManager" take this file to your Dingo 


# Running on Dingo
Runing script on Dingo is done with command like this, you need quotes also you need to be in directory where your script is !

`./energyManager "your connection string"`
