#ifndef __key_h__
#define __key_h__
#include<stdbool.h>
#include<stdint.h>

typedef enum key_event_t {
    key_event_up = 0,
    key_event_down,
    key_event_click
} key_event_t;

typedef enum key_status_t {
    key_status_released = 0,
    key_status_pressed
} key_status_t;

typedef void event_handler_fn(key_event_t event);
typedef struct key_t key_t;
typedef struct key_ops_t {
    void            (*Tick)                 (key_t *key, uint32_t wTimeElapseMillis);
    void            (*SetOnEventListener)   (key_t *key, event_handler_fn *fnHandler);
    key_status_t    (*ReadKeyIOStatus)      (key_t *key);
    void            (*OnEvent)              (key_t *key, key_event_t tEvent);
} key_ops_t;

struct key_t {
    key_ops_t *ops;

    uint8_t chId;
    key_status_t tLastKeyStatus;
    uint32_t wTimer;
    uint32_t wPressTime;
};

#endif /* __key_h__ */
