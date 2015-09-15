# NiDBUploader

This project is for a GUI based program which uploads MRI, EEG, and other binary data to an instance of the Neuroinformatics Database (NiDB). See NiDB project at http://github.com/gbook/nidb.

**Pre-requisites** (Windows and Linux)

* QT open-source, including QT Creator
* GCC, libstd, etc
* cmake

**Setup build environment** (Linux)

    cd ~
    svn export https://github.com/gbook/nidb/trunk NiDBUploader
    cd NiDBUploader
    mkdir gdcmbin
    cd gdcmbin
    cmake ../gdcm
    make

**Build NiDBUploader** (Linux)

    cd ~
    svn export https://github.com/gbook/nidb/trunk NiDBUploader /* update the code to latest version if necessary */
    cd NiDBUploader
    qtcreator .

Within QTCreator, build and test the project
