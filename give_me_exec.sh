
red=`tput setaf 1`
green=`tput setaf 2`
white=`tput setaf 7`

cd build
echo 'Running the build system..'
if cmake --build .
then 
	echo "${green}Build successful.."
	echo "${white}Formatting code.."
	cd ..
	if indent -linux include/A0/pixel.h
	then
		rm include/A0/pixel.h~
	else
		echo "${red}Formatting failed!. Make sure you have GNU Indent!"
	fi
	echo "${white}Running executable.."
	./build/app
else
	cd ..
	echo "${red}Build failed!"
fi
