#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from . import session
from .models.data import Data
from datetime import datetime
from multiprocessing import Process
import socket, sys


def test():
    data = Data(attribute="test", value="123", unit="℃", created_at=datetime.now(), sensor_id="18328504755")
    session.add(data)
    session.commit()
    print(session.query(Data).all())


def parse(value, format):
    format = format.upper()
    if format == "DEC":
        rs = 0
        for i in value:
            rs = ord(i) + rs * pow(2, 8)
        return rs
    else:
        return value


def store_target(sock, addr):
    """
    accept方法返回socket和一个tuple(addr);tuple是客户端的ip和port
    socket的getpeername返回连接的机器的ip和port;client调用返回server的;server调用返回client的
    getsocketname返回本端的ip和port
    """
    try:
        file = open("log.txt", "w", encoding="utf-8")
        print('Connect from %s: %s .' % addr, file=file)
        rev = sock.recv(2048).decode('utf-8')

        li = rev.split("|")
        for item in li[1:]:
            res = item.split("~")
            if len(res) <= 2:
                break
            attribute, value, unit = res[0], res[1], res[2]
            if len(res) == 4:
                value = parse(value, res[3])
            else:
                break

            data = Data(attribute=attribute, unit=unit, value=value, created_at=datetime.now(), sensor_id=li[0])
            session.add(data)
            session.commit()

        print(rev)

    except BaseException as e:
        print(e)
    finally:
        sock.close()
        print('Connect from %s: %s closed.' % addr)


def run():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # socket.SOCK_STREAM socket.SOCK_DGRAM
    s.bind(('0.0.0.0', 8080))
    s.listen(10)
    while True:
        print("test in...")
        Process(target=store_target, args=s.accept()).start()

