
red=`tput setaf 1`
green=`tput setaf 2`
white=`tput setaf 7`

cd build
echo 'Running the build system..'
if cmake --build .
then 
	echo "${green}Build successful.."
	echo "${white}Running executable.."
	cd ..
	./build/app
else
	cd ..
	echo "${red}Build failed!"
fi
