from setuptools import setup, find_packages

setup(
    name = 'npx',
    version = '0.1',
    packages = find_packages(),

    install_requires = [
        'bitarray==0.3.5'
    ],

    entry_points = {
        'console_scripts': [
            'gen = npx.command:gen',
            'nkeval = npx.command:nkeval'
        ],
    }
)
