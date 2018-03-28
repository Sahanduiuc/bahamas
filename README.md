#Requirements 

 - Visual Studio 2017 - MSVC 14.1

# Getting Started

	Step 1 - Building Boost
		
			- Download boost 1.64.0 from http://www.boost.org/users/history/version_1_64_0.html
			- Extract to C:\boost_1_64_0 (the extracted structure should look like C:\boost_1_64_0\boost_1_64_0)
			- Run bootstrap.bat
			- Copy the build_boost_1_64_vs2017.bat script from source to C:\boost_1_64_0 and run the script to build boost
			- Copy the boost_current property file from source to C:\boost_1_64_0

	Step 2 - Building Core
	
			- Open BahamasSystem_Core.sln
			- In Visual Studio, select View->Property Manager
			- Right click the BahamasSystem_Core project and select "Add Existing Property Sheet..."
			- Select the property sheet found at C:\boost_1_64_0
			- Do the same for the Console project

	Step 3 - Running a new backtest session




