/**********************************************************************
   class:  Event (template class)
   author: Weijing Liu
   date:   May 21, 2013
   Provides a fully functional C#-like-"event" class for C++
**********************************************************************/



#ifndef WL_EVENT_H 
#define WL_EVENT_H 






#include<vector>
#include"eventhandler.h"



namespace wl {   // weijing liu(wl) library namespace
    

    /* This is a template class. It is to provide a mechanism
       that broadcasts the happening event to its subscribers. The parameter 
       1) SenderT is the event owner, 2) ArgT is the event info to tell
       the event subscribers.
     */
    template <class SenderT, class ArgT>    class Event;
    template <class SenderT, class ArgT>    
    class Event<SenderT*,ArgT>
    {  
        
        // event handlers of subcribers, which are the particular functions to call when the event occurs.
        std::vector<details::Base_EventHandler<SenderT*,ArgT,void>* > _handlers;
        

        
       Event(const Event&);
       Event& operator=(const Event&);
        
    public:
        
        Event(){}
        

        virtual ~Event(){}
       

	// Event broadcast operator
	// It is  called usually when the event occurs.
        void operator()(SenderT* sender, ArgT args)
        {
            for (unsigned i = 0; i < _handlers.size(); ++i) 
            {
                (*_handlers[i])(sender, args);
            }
        }
        
        
        
	// Subscription interface for subscribers.
        template <class ObjT, class RetT>
        void Add(ObjT *obj, RetT (ObjT::*memfun)(SenderT *, ArgT))
        {
            _handlers.push_back(new details::EventHandler<ObjT*, SenderT*, ArgT, RetT>(obj, memfun));    
        }
    
    



        template <class ObjT, class RetT>
        void operator+=(details::EventHandler<ObjT*, SenderT*, ArgT, RetT>* handler)
        {
            _handlers.push_back(handler); 
        }
    };
}


#endif
