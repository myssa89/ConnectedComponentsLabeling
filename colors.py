# colorgen.py
#
# Copyright 2011 West - License: Public domain
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# Adapted from http://www.8bitrobot.com/wp-content/uploads/2011/09/colorgen.txt
# and http://stackoverflow.com/questions/4296249/how-do-i-convert-a-hex-triplet-to-an-rgb-tuple-and-back

import sys
import math
import itertools
from decimal import *

HEX = '0123456789abcdef'
HEX2 = dict((a+b, HEX.index(a)*16 + HEX.index(b)) for a in HEX for b in HEX)

def rgb(triplet):
    triplet = triplet.lower()
    return (HEX2[triplet[0:2]], HEX2[triplet[2:4]], HEX2[triplet[4:6]])

def MidSort(lst):
  if len(lst) <= 1:
    return lst
  i = int(len(lst)/2)
  ret = [lst.pop(i)]
  left = MidSort(lst[0:i])
  right = MidSort(lst[i:])
  interleaved = [item for items in itertools.izip_longest(left, right)
    for item in items if item != None]
  ret.extend(interleaved)
  return ret

def GetColors(numColors):
# Build list of points on a line (0 to 255) to use as color 'ticks'
    numColors += 1
    max = 255
    segs = int(numColors**(Decimal("1.0")/3))
    step = int(max/segs)
    p = [(i*step) for i in xrange(1,segs)]
    points = [0,max]
    points.extend(MidSort(p))

# Not efficient!!! Iterate over higher valued 'ticks' first (the points
#   at the front of the list) to vary all colors and not focus on one channel.
    colors = []
    range = 0
    total = 1
    while total < numColors and range < len(points):
      range += 1
      for c0 in xrange(range):
        for c1 in xrange(range):
          for c2 in xrange(range):
            if total >= numColors:
              break
            c = "%02X%02X%02X" % (points[c0], points[c1], points[c2])
            if rgb(c) not in colors:
              colors.append(rgb(c))
              total += 1
    return colors;

