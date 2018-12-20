#! /usr/bin/env python

# Run like this:
#   $ KEY=<YOUR APIKEY> DEVICE=<YOUR DEVICE ID> python export_values.py

import sys, os, time

sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from m2x.client import M2XClient

KEY     = os.environ["KEY"]
DEVICE  = os.environ["DEVICE"]

client = M2XClient(key=KEY)

device = client.device(DEVICE)

res = device.values_export()

location = res.headers["location"]

print "The job location is in %s" % location

job = client.job(location.split("/")[-1])

state = job.state

while state != "complete":

    if state == "failed": sys.exit("Job has failed to complete")

    print "Job state is %s, waiting for completion" % state

    time.sleep(5)

    job = client.job(location.split("/")[-1])

    state = job["state"]

print "The job has been completed! You can download the result from %s" % job.result["url"]
