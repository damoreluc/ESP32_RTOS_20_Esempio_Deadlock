/*
 * FreeRTOS Esercizio 20: concorrenza tra due task e deadlock.
 *
 * Due task devono accedere in modo concorrente alla stessa risorsa; per guadagnare l'accesso, 
 * i task devono acquisire due mutex (mutex_1 e mutex_2).
 * 
 * Il Task A ha priorità alta; il Task B ha priorità bassa.
 * 
 * La soluzione qui proposta non può funzionare, poiché i due task finiscono col bloccarsi a vicenda
 * dopo aver acquisito il loro primo mutex (situazione di deadlock). 
 *
 * Nota: nel file soc.h sono definiti i riferimenti ai due core della ESP32:
 *   #define PRO_CPU_NUM (0)
 *   #define APP_CPU_NUM (1)
 *
 * Qui viene adoperata la APP_CPU
 *
 */

#include <Arduino.h>
#include <GLOBALS/globals.h>
#include <TASK/taskA.h>
#include <TASK/taskB.h>

//*****************************************************************************
// Globals
SemaphoreHandle_t mutex_1 = NULL;
SemaphoreHandle_t mutex_2 = NULL;

//*****************************************************************************
// Main (sul core 1, con priorità 1)

// configurazione del sistema
void setup()
{
  // Configurazione della seriale
  Serial.begin(115200);

  // breve pausa
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println();
  Serial.println("FreeRTOS deadlock: Esempio 1 con due task");

  // Crea i due mutexes prima di avviare i due tasks
  mutex_1 = xSemaphoreCreateMutex();
  mutex_2 = xSemaphoreCreateMutex();

  if(mutex_1 == NULL || mutex_2 == NULL) {
    Serial.println("ERRORE: impossibile creare i mutex");
    ESP.restart();
  }

  // Crea il Task A
  // con priorità più alta 
  xTaskCreatePinnedToCore(
      doTaskA,      // Funzione da eseguire
      "Task A",     // Nome del task
      4096,         // Stack del task
      NULL,         // parametri per il task
      2,            // Livello di priorità aumentato
      NULL,         // Puntatore al task
      APP_CPU_NUM); // Core su sui eseguire il task

  // Crea il Task B
  // con priorità più bassa 
  xTaskCreatePinnedToCore(
      doTaskB,      // Funzione da eseguire
      "Task B",     // Nome del task
      4096,         // Stack del task
      NULL,         // parametri per il task
      1,            // Livello di priorità base
      NULL,         // Puntatore al task
      APP_CPU_NUM); // Core su sui eseguire il task

  // Elimina il task con "Setup e Loop"
  vTaskDelete(NULL);
}

void loop()
{
  // lasciare vuoto
}