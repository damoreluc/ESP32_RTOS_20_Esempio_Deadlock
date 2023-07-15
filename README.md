# ESP32_RTOS_20_Esempio_Deadlock

## FreeRTOS Esercizio 20: concorrenza tra due task e deadlock.

Due task devono accedere in modo concorrente alla stessa risorsa; per guadagnare l'accesso, 
i task devono acquisire due mutex (mutex_1 e mutex_2).

Il Task A ha priorità alta; il Task B ha priorità bassa.
 
La soluzione qui proposta non può funzionare, poiché i due task finiscono col bloccarsi a vicenda
dopo aver acquisito il loro primo mutex (situazione di deadlock).
