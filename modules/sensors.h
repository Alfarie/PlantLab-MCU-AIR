#include <Task.h>
extern TaskManager taskManager;

#include "./air.h"
#include "./co2.h"

class Sensors : public Task
{
  public:
    static Sensors *s_instance;
    Sensors() : Task(MsToTaskTime(1000))
    {
        taskManager.StartTask(Air::instance());
        taskManager.StartTask(CO2::instance());
    }
    static Sensors *instance()
    {
        if (!s_instance)
            s_instance = new Sensors;
        return s_instance;
    }

  private:
    String cmd = "";
    virtual bool OnStart()
    {
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        cmd = "{" + String (Air::instance()->GetTemperature() ) 
        + "," + String (Air::instance()->GetHumidity() ) 
        + "," + String (CO2::instance()->GetCO2() )  + "}";
        toHq.println(cmd);
        Serial.println(cmd);
    }
};

Sensors *Sensors::s_instance = 0;