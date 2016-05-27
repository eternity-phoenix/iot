#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()

engine = create_engine('mysql+mysqldb://root:password@localhost:3306/iot?charset=utf8')

# 创建DBSession类型:
DBSession = sessionmaker(bind=engine)
session = DBSession()
