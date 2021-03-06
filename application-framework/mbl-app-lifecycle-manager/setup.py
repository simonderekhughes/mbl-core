#!/usr/bin/env python3
# Copyright (c) 2018 Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

"""Mbed Linux OS Application Lifecycle Manager package setup.py file."""

import os
from setuptools import setup


def read(fname):
    """Read the content of a file."""
    return open(os.path.join(os.path.dirname(__file__), fname)).read()


setup(
    name="mbl-app-lifecycle-manager",
    version="1",
    description="Mbed Linux OS Application Lifecycle Manager",
    long_description=read("README.md"),
    author="Arm Ltd.",
    license="BSD-3-Clause",
    packages=["mbl.app_lifecycle_manager"],
    zip_safe=False,
    entry_points={
        "console_scripts": [
            "mbl-app-lifecycle-manager = mbl.app_lifecycle_manager.cli:_main"
        ]
    },
)
