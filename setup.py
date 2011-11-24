from setuptools import setup, find_packages
from Cython.Build import cythonize

setup(
    name = 'npx',
    version = '0.1',
    packages = find_packages(),
    ext_modules = cythonize("npx/*.pyx"),

    install_requires = [
        'bitstring==3.0.1'
    ],

    entry_points = {
        'console_scripts': [
            'nkeval = npx.command:nkeval',
            'nkneighbours = npx.command:nkneighbours',
            'bagen = npx.command:bagen',
            'bamtest = npx.command:bamtest',
            'nkbsf = npx.command.nkbsf:main',
            'plot = npx.command.plot:main',
            'plothist = npx.command.plothist:main',
            'plotmse = npx.command.plotmse:main',
            'plotmulti = npx.command.plotmulti:main',
            'stats = npx.command.stats:main',
        ],
    }
)
