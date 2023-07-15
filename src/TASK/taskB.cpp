#include <TASK/taskA.h>
#include <GLOBALS/globals.h>

extern  SemaphoreHandle_t mutex_1;
extern  SemaphoreHandle_t mutex_2;

//*****************************************************************************
// Tasks

// Task B (bassa priorità)
void doTaskB(void *parameters) {

  // Ciclo infinito
  while (1) {

    if (mutex_1 == NULL || mutex_2 == NULL)
    {
      Serial.println("Task B ERRORE: mutex nulli");
      while (1)
      {;
      }
    }

    // Nota: l'ordine di acquisizione dei due mutex è inverso rispetto al Task A
    // Prende il mutex 2 (la pausa di 3ms induce il deadlock con l'altro task)
    xSemaphoreTake(mutex_2, portMAX_DELAY);
    Serial.println("Il Task B prende il mutex 2");
    vTaskDelay( pdMS_TO_TICKS(3) );

    // Prende il mutex 1
    xSemaphoreTake(mutex_1, portMAX_DELAY);
    Serial.println("Il Task B prende il mutex 1");

    // Sezione critica protetta con 2 mutexes
    Serial.println("Il Task B sta elaborando dati...");
    vTaskDelay(pdMS_TO_TICKS(500));

    // Rilascia i mutexes
    Serial.println("Il Task B rilascia il mutex 1");    
    xSemaphoreGive(mutex_1);
    Serial.println("Il Task B rilascia il mutex 2");    
    xSemaphoreGive(mutex_2);

    // Pausa per consentire l'esecuzione dell'altro task
    Serial.println("Il Task B va in pausa");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}