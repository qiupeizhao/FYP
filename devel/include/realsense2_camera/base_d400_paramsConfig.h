//#line 2 "/opt/ros/kinetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
//
// File autogenerated for the realsense2_camera package
// by the dynamic_reconfigure package.
// Please do not edit.
//
// ********************************************************/

#ifndef __realsense2_camera__BASE_D400_PARAMSCONFIG_H__
#define __realsense2_camera__BASE_D400_PARAMSCONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace realsense2_camera
{
  class base_d400_paramsConfigStatics;

  class base_d400_paramsConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l,
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }

      virtual void clamp(base_d400_paramsConfig &config, const base_d400_paramsConfig &max, const base_d400_paramsConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const base_d400_paramsConfig &config1, const base_d400_paramsConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, base_d400_paramsConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const base_d400_paramsConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, base_d400_paramsConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const base_d400_paramsConfig &config) const = 0;
      virtual void getValue(const base_d400_paramsConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;

    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string a_name, std::string a_type, uint32_t a_level,
          std::string a_description, std::string a_edit_method, T base_d400_paramsConfig::* a_f) :
        AbstractParamDescription(a_name, a_type, a_level, a_description, a_edit_method),
        field(a_f)
      {}

      T (base_d400_paramsConfig::* field);

      virtual void clamp(base_d400_paramsConfig &config, const base_d400_paramsConfig &max, const base_d400_paramsConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;

        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const base_d400_paramsConfig &config1, const base_d400_paramsConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, base_d400_paramsConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const base_d400_paramsConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, base_d400_paramsConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const base_d400_paramsConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const base_d400_paramsConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, base_d400_paramsConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string a_name, std::string a_type, int a_parent, int a_id, bool a_s, T PT::* a_f) : AbstractGroupDescription(a_name, a_type, a_parent, a_id, a_s), field(a_f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, base_d400_paramsConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<base_d400_paramsConfig::AbstractGroupDescriptionConstPtr> groups;
    };

class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(base_d400_paramsConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("base_depth_gain"==(*_i)->name){base_depth_gain = boost::any_cast<int>(val);}
        if("base_depth_enable_auto_exposure"==(*_i)->name){base_depth_enable_auto_exposure = boost::any_cast<bool>(val);}
        if("base_depth_visual_preset"==(*_i)->name){base_depth_visual_preset = boost::any_cast<int>(val);}
        if("base_depth_frames_queue_size"==(*_i)->name){base_depth_frames_queue_size = boost::any_cast<int>(val);}
        if("base_depth_error_polling_enabled"==(*_i)->name){base_depth_error_polling_enabled = boost::any_cast<bool>(val);}
        if("base_depth_output_trigger_enabled"==(*_i)->name){base_depth_output_trigger_enabled = boost::any_cast<bool>(val);}
        if("base_depth_units"==(*_i)->name){base_depth_units = boost::any_cast<double>(val);}
        if("base_JSON_file_path"==(*_i)->name){base_JSON_file_path = boost::any_cast<std::string>(val);}
      }
    }

    int base_depth_gain;
bool base_depth_enable_auto_exposure;
int base_depth_visual_preset;
int base_depth_frames_queue_size;
bool base_depth_error_polling_enabled;
bool base_depth_output_trigger_enabled;
double base_depth_units;
std::string base_JSON_file_path;

    bool state;
    std::string name;

    
}groups;



//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int base_depth_gain;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool base_depth_enable_auto_exposure;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int base_depth_visual_preset;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int base_depth_frames_queue_size;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool base_depth_error_polling_enabled;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool base_depth_output_trigger_enabled;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double base_depth_units;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      std::string base_JSON_file_path;
//#line 218 "/opt/ros/kinetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("base_d400_paramsConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }

    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const base_d400_paramsConfig &__max__ = __getMax__();
      const base_d400_paramsConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const base_d400_paramsConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }

    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const base_d400_paramsConfig &__getDefault__();
    static const base_d400_paramsConfig &__getMax__();
    static const base_d400_paramsConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();

  private:
    static const base_d400_paramsConfigStatics *__get_statics__();
  };

  template <> // Max and min are ignored for strings.
  inline void base_d400_paramsConfig::ParamDescription<std::string>::clamp(base_d400_paramsConfig &config, const base_d400_paramsConfig &max, const base_d400_paramsConfig &min) const
  {
    (void) config;
    (void) min;
    (void) max;
    return;
  }

  class base_d400_paramsConfigStatics
  {
    friend class base_d400_paramsConfig;

    base_d400_paramsConfigStatics()
    {
base_d400_paramsConfig::GroupDescription<base_d400_paramsConfig::DEFAULT, base_d400_paramsConfig> Default("Default", "", 0, 0, true, &base_d400_paramsConfig::groups);
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_gain = 16;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_gain = 248;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_gain = 16;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_gain", "int", 1, "Gain", "", &base_d400_paramsConfig::base_depth_gain)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_gain", "int", 1, "Gain", "", &base_d400_paramsConfig::base_depth_gain)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_enable_auto_exposure = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_enable_auto_exposure = 1;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_enable_auto_exposure = 1;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_enable_auto_exposure", "bool", 2, "Enable Auto Exposure", "", &base_d400_paramsConfig::base_depth_enable_auto_exposure)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_enable_auto_exposure", "bool", 2, "Enable Auto Exposure", "", &base_d400_paramsConfig::base_depth_enable_auto_exposure)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_visual_preset = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_visual_preset = 5;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_visual_preset = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_visual_preset", "int", 3, "D400 Visual Presets", "{'enum_description': 'D400 Visual Presets', 'enum': [{'srcline': 10, 'description': 'Custom', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'Custom'}, {'srcline': 11, 'description': 'Default Preset', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'Default'}, {'srcline': 12, 'description': 'Hand Gesture', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'Hand'}, {'srcline': 13, 'description': 'High Accuracy', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 3, 'ctype': 'int', 'type': 'int', 'name': 'HighAccuracy'}, {'srcline': 14, 'description': 'High Density', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 4, 'ctype': 'int', 'type': 'int', 'name': 'HighDensity'}, {'srcline': 15, 'description': 'Medium Density', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 5, 'ctype': 'int', 'type': 'int', 'name': 'MediumDensity'}]}", &base_d400_paramsConfig::base_depth_visual_preset)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_visual_preset", "int", 3, "D400 Visual Presets", "{'enum_description': 'D400 Visual Presets', 'enum': [{'srcline': 10, 'description': 'Custom', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'Custom'}, {'srcline': 11, 'description': 'Default Preset', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'Default'}, {'srcline': 12, 'description': 'Hand Gesture', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'Hand'}, {'srcline': 13, 'description': 'High Accuracy', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 3, 'ctype': 'int', 'type': 'int', 'name': 'HighAccuracy'}, {'srcline': 14, 'description': 'High Density', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 4, 'ctype': 'int', 'type': 'int', 'name': 'HighDensity'}, {'srcline': 15, 'description': 'Medium Density', 'srcfile': '/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py', 'cconsttype': 'const int', 'value': 5, 'ctype': 'int', 'type': 'int', 'name': 'MediumDensity'}]}", &base_d400_paramsConfig::base_depth_visual_preset)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_frames_queue_size = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_frames_queue_size = 32;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_frames_queue_size = 16;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_frames_queue_size", "int", 4, "Frames Queue Size", "", &base_d400_paramsConfig::base_depth_frames_queue_size)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<int>("base_depth_frames_queue_size", "int", 4, "Frames Queue Size", "", &base_d400_paramsConfig::base_depth_frames_queue_size)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_error_polling_enabled = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_error_polling_enabled = 1;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_error_polling_enabled = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_error_polling_enabled", "bool", 5, "Error Polling Enabled", "", &base_d400_paramsConfig::base_depth_error_polling_enabled)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_error_polling_enabled", "bool", 5, "Error Polling Enabled", "", &base_d400_paramsConfig::base_depth_error_polling_enabled)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_output_trigger_enabled = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_output_trigger_enabled = 1;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_output_trigger_enabled = 0;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_output_trigger_enabled", "bool", 6, "Output Trigger Enabled", "", &base_d400_paramsConfig::base_depth_output_trigger_enabled)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<bool>("base_depth_output_trigger_enabled", "bool", 6, "Output Trigger Enabled", "", &base_d400_paramsConfig::base_depth_output_trigger_enabled)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_depth_units = 0.001;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_depth_units = 0.001;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_depth_units = 0.001;
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<double>("base_depth_units", "double", 7, "Depth Units", "", &base_d400_paramsConfig::base_depth_units)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<double>("base_depth_units", "double", 7, "Depth Units", "", &base_d400_paramsConfig::base_depth_units)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.base_JSON_file_path = "";
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.base_JSON_file_path = "";
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.base_JSON_file_path = "";
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<std::string>("base_JSON_file_path", "str", 8, "JSON_file_path", "", &base_d400_paramsConfig::base_JSON_file_path)));
//#line 292 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(base_d400_paramsConfig::AbstractParamDescriptionConstPtr(new base_d400_paramsConfig::ParamDescription<std::string>("base_JSON_file_path", "str", 8, "JSON_file_path", "", &base_d400_paramsConfig::base_JSON_file_path)));
//#line 245 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 245 "/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(base_d400_paramsConfig::AbstractGroupDescriptionConstPtr(new base_d400_paramsConfig::GroupDescription<base_d400_paramsConfig::DEFAULT, base_d400_paramsConfig>(Default)));
//#line 356 "/opt/ros/kinetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<base_d400_paramsConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__);
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__);
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__);
    }
    std::vector<base_d400_paramsConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<base_d400_paramsConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    base_d400_paramsConfig __max__;
    base_d400_paramsConfig __min__;
    base_d400_paramsConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const base_d400_paramsConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static base_d400_paramsConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &base_d400_paramsConfig::__getDescriptionMessage__()
  {
    return __get_statics__()->__description_message__;
  }

  inline const base_d400_paramsConfig &base_d400_paramsConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }

  inline const base_d400_paramsConfig &base_d400_paramsConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }

  inline const base_d400_paramsConfig &base_d400_paramsConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }

  inline const std::vector<base_d400_paramsConfig::AbstractParamDescriptionConstPtr> &base_d400_paramsConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<base_d400_paramsConfig::AbstractGroupDescriptionConstPtr> &base_d400_paramsConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const base_d400_paramsConfigStatics *base_d400_paramsConfig::__get_statics__()
  {
    const static base_d400_paramsConfigStatics *statics;

    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = base_d400_paramsConfigStatics::get_instance();

    return statics;
  }

//#line 10 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_Custom = 0;
//#line 11 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_Default = 1;
//#line 12 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_Hand = 2;
//#line 13 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_HighAccuracy = 3;
//#line 14 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_HighDensity = 4;
//#line 15 "/home/rover1/catkin_ws/src/rover_hardware/realsense/realsense2_camera/cfg/base_d400_params.py"
      const int base_d400_params_MediumDensity = 5;
}

#endif // __BASE_D400_PARAMSRECONFIGURATOR_H__
