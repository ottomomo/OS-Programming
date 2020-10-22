#!/bin/bash
# Scripth de arranque de daemon sincro
# interfaz grafica hecha con zenity
# @Autores: Octavio Sales y Jorge Lopez

#while [[ opc != 0 ]]
#clear 
#do

#opc=$(zenity --width=320 --height=220 --title=DaemonSincro --entry --text=" Selecciona una opción
#      1) Start
#      2) Stop
#      3) Reload
#      4) Force
#      0) Exit "
#)
#case $opc in
#"1")
#./sincro
#;;
#"2")
#;;
#"0")
#zenity --notification --text "Are you sure?"
#  exit 0
#;;
#esac
#done


function _menu()
{
        echo ""
        echo "				___________DAEMON SINCRO___________"
        echo 
        echo
        echo "				(1) Start Daemon Sincro"
        echo "				(2) Stop Daemon Sincro"
        echo "				(3) Reload Daemon Sincro"
        echo "				(4) Force Daemon Sincro"
        echo
        echo "				(0) exit"
        echo "				____________________________________"
}


opc=7
exit=0

until [ $exit -eq 1 ]
do
    case $opc in
        1)
            echo -n "Starting daemon: executing ./sincro..."
            echo
            ./sincro
            echo "."
            _menu
            echo
            echo "Choose an action:"
            ;;
        2)
            echo -n "Stopping daemon: sending SIGNAL TERM..."
            echo
            FICHERO=/.sincro.lock
            DIRECTORIO=`echo -n $HOME`
            ACCESO=$DIRECTORIO$FICHERO
	    if [ -f $ACCESO ]; 
	    then
		VALUE=$(<$ACCESO)	
		kill -SIGTERM $VALUE
	    else
		echo "* WARNING: The daemon was not started. *"
	    fi
            echo ""
            
            _menu
            echo
            echo "Choose an action:"
            ;;
        3)
            echo -n "Reloading daemon: sending SIGNAL HANGUP..." 
            echo
            FICHERO=/.sincro.lock
            DIRECTORIO=`echo -n $HOME`
            ACCESO=$DIRECTORIO$FICHERO
            if [ -f $ACCESO ]; 
            then
		VALUE=$(<$ACCESO)  	
		kill -SIGHUP $VALUE
	    else
	      echo "* WARNING: The daemon is not started. Select the action 1 to start the daemon. *"
	    fi
            echo ""
            _menu
            echo
            echo "Choose an action:"
            ;;
        4)
            echo -n "Forcing daemon: sending SIGNAL USR1..." 
            echo 
            FICHERO=/.sincro.lock
            DIRECTORIO=`echo -n $HOME`
            ACCESO=$DIRECTORIO$FICHERO
            if [ -f $ACCESO ]; 
            then
		VALUE=$(<$ACCESO)	
		kill -SIGUSR1 $VALUE
	    else
	      echo "* WARNING: The daemon is not started. Select the action 1 to start the daemon. *"
	    fi
            echo ""
            _menu
            echo
            echo "Choose an action:"
            ;;
        0)
	    exit=1
	    echo "*GOOD BYE!"
	    exit 0
	    ;;
        *)
            _menu
            echo
            echo "Choose an action:"
            ;;
    esac
    read opc
done

