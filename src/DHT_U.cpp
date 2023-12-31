
#include "DHT_U.h"

DHT_Unified::DHT_Unified(uint8_t pin, uint8_t type, uint8_t count,int32_t tempSensorId, int32_t humiditySensorId): _dht(pin, type, count), _type(type), _temp(this, tempSensorId), _humidity(this, humiditySensorId) {}

void DHT_Unified::begin() { _dht.begin(); }
void DHT_Unified::setName(sensor_t *sensor)
{
  switch (_type)
  {
  case DHT11:
    strncpy(sensor->name, "DHT11", sizeof(sensor->name) - 1);
    break;
  default:
    strncpy(sensor->name, "DHT?", sizeof(sensor->name) - 1);
    break;
  }
  sensor->name[sizeof(sensor->name) - 1] = 0;
}
void DHT_Unified::setMinDelay(sensor_t *sensor)
{
  switch (_type)
  {
  case DHT11:
    sensor->min_delay = 1000000L; // 1 second (in microseconds)
    break;
  default:
    // Default to slowest sample rate in case of unknown type.
    sensor->min_delay = 2000000L; // 2 seconds (in microseconds)
    break;
  }
}
DHT_Unified::Temperature::Temperature(DHT_Unified *parent, int32_t id) : _parent(parent), _id(id) {}
bool DHT_Unified::Temperature::getEvent(sensors_event_t *event)
{
  // Clear event definition.
  memset(event, 0, sizeof(sensors_event_t));
  // Populate sensor reading values.
  event->version = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  event->timestamp = millis();
  event->temperature = _parent->_dht.readTemperature();
  return true;
}
void DHT_Unified::Temperature::getSensor(sensor_t *sensor)
{
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  _parent->setName(sensor);
  // Set version and ID
  sensor->version = DHT_SENSOR_VERSION;
  sensor->sensor_id = _id;
  // Set type and characteristics.
  sensor->type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  _parent->setMinDelay(sensor);
  switch (_parent->_type)
  {
  case DHT11:
    sensor->max_value = 50.0F;
    sensor->min_value = 0.0F;
    sensor->resolution = 2.0F;
    break;
  default:
    // Unknown type, default to 0.
    sensor->max_value = 0.0F;
    sensor->min_value = 0.0F;
    sensor->resolution = 0.0F;
    break;
  }
}
DHT_Unified::Humidity::Humidity(DHT_Unified *parent, int32_t id): _parent(parent), _id(id) {}
bool DHT_Unified::Humidity::getEvent(sensors_event_t *event)
{
  // Clear event definition.
  memset(event, 0, sizeof(sensors_event_t));
  // Populate sensor reading values.
  event->version = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type = SENSOR_TYPE_RELATIVE_HUMIDITY;
  event->timestamp = millis();
  event->relative_humidity = _parent->_dht.readHumidity();
  return true;
}
void DHT_Unified::Humidity::getSensor(sensor_t *sensor)
{
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  _parent->setName(sensor);
  // Set version and ID
  sensor->version = DHT_SENSOR_VERSION;
  sensor->sensor_id = _id;
  // Set type and characteristics.
  sensor->type = SENSOR_TYPE_RELATIVE_HUMIDITY;
  _parent->setMinDelay(sensor);
  switch (_parent->_type)
  {
  case DHT11:
    sensor->max_value = 80.0F;
    sensor->min_value = 20.0F;
    sensor->resolution = 5.0F;
    break;
  default:
    // Unknown type, default to 0.
    sensor->max_value = 0.0F;
    sensor->min_value = 0.0F;
    sensor->resolution = 0.0F;
    break;
  }
}
