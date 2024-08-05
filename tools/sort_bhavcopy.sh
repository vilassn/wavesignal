#!/bin/sh

# A simple script to sort faulty bhavcopy (http://bigdatums.net/2017/06/06/linux-sort-command-examples)

sort_bhavcopy1()
{ 
CSV_FILE=$1 
sed -i 's/29-Aug-2019/A_TMP/g' $CSV_FILE
sed -i 's/26-Sep-2019/B_TMP/g' $CSV_FILE
sed -i 's/31-Oct-2019/C_TMP/g' $CSV_FILE

sort -t ',' -k1,3 $CSV_FILE > $CSV_FILE.tmp
mv $CSV_FILE.tmp $CSV_FILE

sed -i 's/A_TMP/29-Aug-2019/g' $CSV_FILE
sed -i 's/B_TMP/26-Sep-2019/g' $CSV_FILE
sed -i 's/C_TMP/31-Oct-2019/g' $CSV_FILE

sed -i 's/.0000000//g' $CSV_FILE
sed -i 's/00000//g' $CSV_FILE
}

sort_bhavcopy2()
{ 
CSV_FILE=$1 
sed -i 's/29-Apr-2021/A_TMP/g' $CSV_FILE
sed -i 's/27-May-2021/B_TMP/g' $CSV_FILE
sed -i 's/24-Jun-2021/C_TMP/g' $CSV_FILE

sort -t ',' -k1,3 $CSV_FILE > $CSV_FILE.tmp
mv $CSV_FILE.tmp $CSV_FILE

sed -i 's/A_TMP/29-Apr-2021/g' $CSV_FILE
sed -i 's/B_TMP/27-May-2021/g' $CSV_FILE
sed -i 's/C_TMP/24-Jun-2021/g' $CSV_FILE

sed -i 's/.0000000//g' $CSV_FILE
sed -i 's/00000//g' $CSV_FILE
}

sort_bhavcopy3()
{ 
CSV_FILE=$1 
sed -i 's/23-Feb-2023/A_TMP/g' $CSV_FILE
sed -i 's/29-Mar-2023/B_TMP/g' $CSV_FILE
sed -i 's/27-Apr-2023/C_TMP/g' $CSV_FILE

sort -t ',' -k1,3 $CSV_FILE > $CSV_FILE.tmp
mv $CSV_FILE.tmp $CSV_FILE

sed -i 's/A_TMP/23-Feb-2023/g' $CSV_FILE
sed -i 's/B_TMP/29-Mar-2023/g' $CSV_FILE
sed -i 's/C_TMP/27-Apr-2023/g' $CSV_FILE

sed -i 's/.0000000//g' $CSV_FILE
sed -i 's/00000//g' $CSV_FILE
}

# Sort fo28AUG2019bhav.csv to fix OI indicator exception
echo "Start of script..."
#sort_bhavcopy1 appdata/datafeed/historical/2019/fo/fo28AUG2019bhav.csv
#sort_bhavcopy2 appdata/datafeed/historical/2021/fo/fo30MAR2021bhav.csv
sort_bhavcopy3 appdata/datafeed/historical/2023/fo/fo13FEB2023bhav.csv
echo "End of script..."
