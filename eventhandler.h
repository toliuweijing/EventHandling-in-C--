//
//  base_event.h
//  delegation
//
//  Created by 刘纬经 Liu on 5/7/12.
//  Copyright (c) 2012 New York University. All rights reserved.
//
//  Funtionality: it wraps up objects and provides a "event-broadcast" operation
//  it works with the event class.



#ifndef WL_EVENTHANDLER_H 
#define WL_EVENTHANDLER_H 





namespace wl {
  namespace details{ // hide complicated implementation
    


    // class template:      Base_EventHandler
    // class type:          abstract class 
    // description:         provide interface: broadcast operation. 
    template <class SenderT, class ArgT, class RetT>     class Base_EventHandler;
    template <class SenderT, class ArgT, class RetT>  
    class Base_EventHandler<SenderT*, ArgT, RetT>
    {
    public:
        virtual ~Base_EventHandler(){} 

	// Event broadcast operation
        virtual RetT operator()(SenderT* sender, ArgT args) = 0;
    };
    
    
    
    
    
    
    
    
    
    // EventHandler 
    // Constraints on the first 2 argument to be pointer types;
    template <class ObjT, class SenderT, class ArgT, class RetT> class EventHandler;
    template <class ObjT, class SenderT, class ArgT, class RetT>
    class EventHandler<ObjT*, SenderT*, ArgT, RetT> : public Base_EventHandler<SenderT*, ArgT, RetT>
    {
        
        typedef RetT (ObjT::*MemFunT) (SenderT*,ArgT);
        
        
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

template <class ObjT, class SenderT, class ArgT, class RetT>
details::EventHandler<ObjT*, SenderT*, ArgT, RetT>* 
Subscriber(ObjT* obj, RetT (ObjT::*memfun)(SenderT*, ArgT))
{
    return new details::EventHandler<ObjT*,SenderT*,ArgT,RetT>(obj,memfun);
}
}

#endif
