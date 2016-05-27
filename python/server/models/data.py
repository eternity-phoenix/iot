#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from . import Base
from sqlalchemy import Column, Integer, DateTime, String


class Data(Base):
    __tablename__ = 'data'

    id = Column(Integer(), index=True, nullable=False, unique=True, primary_key=True)
    attribute = Column(String(50), nullable=False, index=True)
    created_at = Column(DateTime, nullable=False)
    value = Column(String(1000), nullable=False)
    unit = Column(String(1000), nullable=False)
    sensor_id = Column(String(50), nullable=False, index=True)

    def export_data(self):
        return {
            "id": self.id,
            "attribute": self.attribute,
            "created_at": self.created_at,
            "value": self.value,
            "unit": self.unit,
            "sensor_id": self.sensor_id,
        }
