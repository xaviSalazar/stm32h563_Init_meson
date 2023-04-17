#
#!/bin/bash

serials=(/dev/ttyACM*)

echo "Available TTYs:  ${serials[@]}"

tty_index=$(( ${1:-${#serials[@]}} - 1 ))

filename=${serials[$tty_index]}

if [ -z $filename ]
then
  echo "No TTY chosen."
  exit 3
fi

echo "Choosing TTY #$((1+${tty_index})): $filename"

# -
# --- Configure TTY
# -

BAUDRATE=9600

stty -F $filename $BAUDRATE \
  raw \
  -hup \
  -iexten \
  -echo -echoe -echok -echoctl -echoke

echo -e "\nTTY Configuration:"
stty -F $filename

# -
# --- Commands summary
# -

cat <<EOF

============================
Send Commands Key
============================
sS (activates LED2 in stm32)

EOF

