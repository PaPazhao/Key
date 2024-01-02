#include "key.h"

void key_tick(key_t *self, uint32_t wTimeElapseMillis) {
    self->wTimer += wTimeElapseMillis;
    
    key_status_t pinIOStatus = self->ops->ReadKeyIOStatus(self->chId);

    if(self->tLastKeyStatus != pinIOStatus) {
        if(pinIOStatus == key_status_released) {
            self->ops->OnEvent(self, key_event_up);
            self->wPressTime = 0;
        } else {
            if(!self->wPressTime) {
                self->wPressTime = self->wTimer;
            }
            if(self->wTimer > self->wPressTime + 10) {
                self->ops->OnEvent(self, key_event_down);
            }
        }

        self->tLastKeyStatus = pinIOStatus;
    }
}

static key_ops_t s_tOps = {0};

void key_init(key_t *self, event_handler_fn *fnHandler) {
    self->ops = &s_tOps;
}

void key_set_on_event_listener(key_t *self, event_handler_fn *fnHandler) {
    self->tLastKeyStatus = self->ops->ReadKeyIOStatus(self->chId);
    self->ops->OnEvent = fnHandler;
}


__attribute__((weak)) key_status_t readKeyIOStatus(key_t *key) {
    return key_status_released;
}

