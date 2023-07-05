#include <DHT11.h>

#define INA 3
#define INB 2
#define LED 9
DHT11 dht11(5);

void setup()
{
  Serial.begin(9600);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop()
{
    float humidity = dht11.readHumidity();
    float temperature = dht11.readTemperature();

    if (temperature != -1 && humidity != -1)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        Serial.print("\n");
    }
    else
    {
        // If the temperature or humidity reading failed, print an error message.
        Serial.println("Error reading data");
    }

    delay(2000);
    // Wait for 2 seconds before the next reading.
    
  if(temperature>=25)
  {
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
    digitalWrite(LED, HIGH);
  }
  if(temperature < 25)
  {
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    digitalWrite(LED, LOW);
  }
}
