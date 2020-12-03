#! /bin/bsah

ping -c 3 -i 0.2 -W 3 $1 &> ./test 
if [ $? -eq 0 ]
then
echo "Host: $1 is on line"
else
echo "Host: $1 is not on line"
fi
  
