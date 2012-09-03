//
//  base_event.h
//  delegation
//
//  Created by 刘纬经 Liu on 5/7/12.
//  Copyright (c) 2012 New York University. All rights reserved.
//

#ifndef delegation_base_event_h
#define delegation_base_event_h

namespace wl {
  namespace details{ // hide complicated implementation
    


    // Base_EventHandler
    // Constraints on the 1st Template Argument: SenderT to be a pointer type.
    template <class SenderT, class ArgT>     class Base_EventHandler;
    template <class SenderT, class ArgT>  
    class Base_EventHandler<SenderT*, ArgT>
    {
    public:
        virtual ~Base_EventHandler(){} 

	// Event broadcast operation
        virtual void operator()(SenderT* sender, ArgT args) = 0;
    };
    
    
    
    
    
    
    
    
    
    // EventHandler 
    // Constraints on the first 2 argument to be pointer types;
    template <class ObjT, class SenderT, class ArgT> class EventHandler;
    template <class ObjT, class SenderT, class ArgT>
    class EventHandler<ObjT*, SenderT*, ArgT> : public Base_EventHandler<SenderT*, ArgT>
    {
        
        typedef void (ObjT::*MemFunT) (SenderT*,ArgT);
        
        
        ObjT* _obj; // refer, not own
        MemFunT _fun;
        
        
        
    public:
        ~EventHandler()
        {
        }
        
        
        EventHandler(ObjT* obj, MemFunT memfun):
            _obj(obj),
            _fun(memfun)
        {
            
        }
        
        
        virtual void operator()(SenderT* sender, ArgT args)
        {
            (_obj->*_fun)(sender, args);
        }
    };
    
    
}
}

#endif
