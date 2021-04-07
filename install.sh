#!/bin/bash
if [ ! $(command -v wget) ]; then
    echo "please install wget"
    exit 0
fi

if [ ! $(command -v make) ]; then
    echo "please install make"
    exit 0
fi

if [ -f  /bin/checker ]; then
    echo -e "\e[33mwarning: remove /bin/checker\e[0m"
    sudo rm /bin/checker
fi
if [ -f  /usr/bin/checker ]; then
    echo -e "\e[33mwarning: remove /usr/bin/checker\e[0m"
    sudo rm /usr/bin/checker
fi
if [ -f  /usr/local/bin/checker ]; then
    echo -e "\e[33mwarning: remove /usr/local/bin/checker\e[0m"
    sudo rm /usr/local/bin/checker
fi
if [ -f /tmp/checker/source ]; then
    rm -rf /tmp/checker/source
fi

echo -e "\e[1;32m[download file] ...\e[0m"
rm -rf /tmp/checker/source/
mkdir -p /tmp/checker/source/
cp -r ./ /tmp/checker/source/
cd /tmp/checker/source/

echo -e "\e[1;32m[compile] ...\e[0m"
make
echo -e "\e[1;32m[copy file] ...\e[0m"
sudo sh ./copy.sh
sudo chmod 777 /usr/local/bin/checker
mkdir -p /tmp/checker/update
cp /tmp/checker/source/update.sh /tmp/checker/update/update.sh
sudo chmod 777 /tmp/checker/update/update.sh
