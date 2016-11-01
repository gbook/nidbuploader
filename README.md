# NiDBUploader

This project is for a GUI based program which uploads MRI, EEG, and other binary data to an instance of the Neuroinformatics Database (NiDB). See NiDB project at http://github.com/gbook/nidb.

**Pre-requisites** (Windows and Linux)

* QT open-source 5.x, including QT Creator
* GCC, libstd, etc
* cmake
 
**Windows 7 32/64-bit - Setup build environment**

* Install Visual C++ 2012 Express
* Install TortoiseGit and GitForWindows
* Install CMake 3.x or newer
* Make sure all Windows and Visual Studio updates are applied
* May need to reboot a few times during all of the installs
* Open Windows Explorer, find a place to put the NiDBUploader code
* Right-click somewhere and select **Git Clone...** from context menu
* URL should be "https://github.com/gbook/nidbuploader.git". Click Ok, and the source code will be downloaded
* Open cmake-gui. Select the source directory as ~/nidbuploader/gdcm and the build directory as ~nidbuploader/gdcm-win7
* Click **Configure**. Select the "Visual Studio 11 2012" compiler, click **Finish**.
* Check off the **GDCM_BUILD_SHARED_LIBS** option, click **Configure**. Click **Generate**.
* Go into the ~/nidbuploader/gdcm-win7 directory and open the GDCM.sln file in Visual Studio 2012
* Go to the **BUILD-->Configuration...** menu option. Change the Active solution to *Release*
* On the main Visual Studio window, right click the **ALL_BUILD** project and click **Build**
* Go to the **BUILD-->Configuration...** menu option. Change the Active solution to *Debug*
* On the main Visual Studio window, right click the **ALL_BUILD** project and click **Build**
* The gdcm libraries will then be built
 
**Windows 7 - Build NiDBUPloader**

* Double-click the NiDBUploader.pro file
* The build kits should already established
* Select a **Release** build and build it

**Linux - Setup build environment**

    cd ~
    svn export https://github.com/gbook/nidbuploader/trunk NiDBUploader
    cd NiDBUploader
    mkdir gdcmbin
    cd gdcmbin
    cmake -DGDCM_BUILD_SHARED_LIBS=ON ../gdcm
    make
    make install

**Linux - Build NiDBUploader**

    cd ~
    svn export https://github.com/gbook/nidb/trunk NiDBUploader /* update the code to latest version if necessary */
    cd NiDBUploader
    qtcreator .

Within QTCreator, build and test the project. Make sure it is a Release build.

**Zip the package** (Linux)

QTCreator will create a directory called something like `build-NiDBUploader-Desktop_Qt_5_6_GCC_64bit-Release`. The NiDBUploader binaries will be in there. The /opt/Qt/5.3 directory may be different.

    cp nidbuploader/NiDBUploader.sh build-NiDBUploader-Desktop_Qt_5_6_GCC_64bit-Release
    cd build-NiDBUploader-Desktop_Qt_5_6_GCC_64bit-Release
    chmod 777 NiDBUploader.sh
    cp ../NiDBUploader/gdcmbin/bin/* .
    mkdir platforms
    cd platforms
    cp /opt/Qt/5.6/gcc_64/plugins/platforms/* .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5DBus.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Gui.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Core.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Widgets.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Network.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Test.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libicu* .
    cd ..
    cp /opt/Qt/5.6/gcc_64/plugins/platforms/* .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5DBus.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Gui.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Core.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Widgets.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Network.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libQt5Test.so.5 .
    cp /opt/Qt/5.6/gcc_64/lib/libicu* .
    cd ../..
    zip -r NiDBUploader-<LinuxVer>-<builddate>.zip build-NiDBUploader-Desktop_Qt_5_6_GCC_64bit-Release/*
