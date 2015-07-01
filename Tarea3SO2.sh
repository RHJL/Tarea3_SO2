#!/bin/sh
 
case "$1" in
        start)
              /usr/sbin/Tarea3SO2
              ;;
        stop)
              test -e /var/run/Tarea3SO2.pid || exit 2
              kill `cat /var/run/Tarea3SO2.pid`
              ;;
	restart)
		/usr/sbin/Tarea3SO2
		;;
        *)
              echo "El uso es: $0 {start|stop|restart}"
              exit 1
              ;;
esac
exit 0
