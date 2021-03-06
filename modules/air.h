#include <Task.h>
#include <LibHumidity.h>

extern TaskManager taskManager;
LibHumidity gy21 = LibHumidity(0);

class Air : public Task
{
  public:
    static Air *s_instance;
    Air() : Task(MsToTaskTime(1000))
    {
        temperature = 0;
        humidity = 0;
        vpd = 0;
    }
    static Air *instance()
    {
        if (!s_instance)
            s_instance = new Air;
        return s_instance;
    }
    float GetTemperature()
    {
        return temperature;
    }
    float GetHumidity()
    {
        return humidity;
    }
    float GetVpd()
    {
        return vpd;
    }

  private:
    float temperature, humidity, vpd;
    virtual bool OnStart()
    {
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        temperature = gy21.GetTemperatureC();
        humidity = gy21.GetHumidity();
        vpd = VpdCal(temperature, humidity);
    }

    float VpdCal(float t, float rh)
    {
        float spv = (610.7) * pow(10, ((7.5 * t) / (237.3 + t)));
        return (1 - (rh / 100)) * spv;
    }
};
Air *Air::s_instance = 0;