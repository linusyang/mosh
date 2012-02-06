#ifndef PARSERSTATE_HPP
#define PARSERSTATE_HPP

#include "parsertransition.h"

namespace Parser {
  class StateFamily;

  class State
  {
  protected:
    virtual Transition input_state_rule( wchar_t ch ) const = 0;
    StateFamily *family;

  private:
    Transition anywhere_rule( wchar_t ch ) const;

  public:
    void setfamily( StateFamily *s_family ) { family = s_family; }
    Transition input( wchar_t ch ) const;
    virtual Action *enter( void ) const { return new Ignore; }
    virtual Action *exit( void ) const { return new Ignore; }

    State() : family( NULL ) {};
    virtual ~State() {};

    State( const State & );
    State & operator=( const State & );
  };

  class Ground : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };

  class Escape : public State {
    Action *enter( void ) const;
    Transition input_state_rule( wchar_t ch ) const;
  };

  class Escape_Intermediate : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };

  class CSI_Entry : public State {
    Action *enter( void ) const;
    Transition input_state_rule( wchar_t ch ) const;
  };
  class CSI_Param : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
  class CSI_Intermediate : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
  class CSI_Ignore : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
  
  class DCS_Entry : public State {
    Action *enter( void ) const;
    Transition input_state_rule( wchar_t ch ) const;
  };
  class DCS_Param : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
  class DCS_Intermediate : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
  class DCS_Passthrough : public State {
    Action *enter( void ) const;
    Transition input_state_rule( wchar_t ch ) const;
    Action *exit( void ) const;
  };
  class DCS_Ignore : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };

  class OSC_String : public State {
    Action *enter( void ) const;
    Transition input_state_rule( wchar_t ch ) const;
    Action *exit( void ) const;
  };
  class SOS_PM_APC_String : public State {
    Transition input_state_rule( wchar_t ch ) const;
  };
}

#endif