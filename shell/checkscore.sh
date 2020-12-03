#! /bin/bash
read -p "Enter your acore(0-100):" GRADE
if [ $GRADE -ge 85 ] && [ $GRADE -le 100 ]
then 
echo "$GRADE is excellent"
elif [ $GRADE -ge 74 ] && [ $GRADE -le 84 ] 
then 
echo "$GRADE is pass"
else 
echo "$GRADE is fail"
fi
