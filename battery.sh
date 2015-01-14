FILE="/home/robert/battery/battery.log"

date=`date "+%d.%m.%Y %H:%M"`

percent=`upower -i /org/freedesktop/UPower/devices/battery_BAT1 | egrep -e "percentage" | tr -s ' ' | cut -d ':' -f2`

echo "$date$percent" >> $FILE
