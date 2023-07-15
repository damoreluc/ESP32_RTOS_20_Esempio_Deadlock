#include <TASK/taskA.h>
#include <GLOBALS/globals.h>

extern  SemaphoreHandle_t mutex_1;
extern  SemaphoreHandle_t mutex_2;

//*****************************************************************************
// Tasks

// Task A (alta priorità)
void doTaskA(void *parameters)
{

  // Ciclo infinito
  while (1)
  {

    if (mutex_1 == NULL || mutex_2 == NULL)
    {
      Serial.println("Task A ERRORE: mutex nulli");
      while (1)
      {;
      }
    }

    // Prende il mutex 1 (la pausa di 3ms induce il deadlock con l'altro task)
    xSemaphoreTake(mutex_1, portMAX_DELAY);
    Serial.println("Il Task A prende il mutex 1");
    vTaskDelay(pdMS_TO_TICKS(3));

    // Prende il mutex 2
    xSemaphoreTake(mutex_2, portMAX_DELAY);
    Serial.println("Il Task A prende il mutex 2");

    // Sezione critica protetta con 2 mutexes
    Serial.println("Il Task A sta elaborando dati...");
    vTaskDelay(pdMS_TO_TICKS(500));

    // Rilascia i mutexes
    Serial.println("Il Task A rilascia il mutex 2");    
    xSemaphoreGive(mutex_2);
    Serial.println("Il Task A rilascia il mutex 1");    
    xSemaphoreGive(mutex_1);

    // Pausa per consentire l'esecuzione dell'altro task
    Serial.println("Il Task A va in pausa");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}