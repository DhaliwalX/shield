//
// Created by malcolm on 26/11/17.
//

#include "IOService.h"

avenger::strange::IOService::IOService() : service_{} {

}

boost::asio::io_service &avenger::strange::IOService::getService() {
    return service_;
}
