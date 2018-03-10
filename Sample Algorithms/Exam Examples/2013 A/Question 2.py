score = 0
def editingDistance (a,b):
    global score
    if (len(a) > len(b)):
        for i, (x,y) in enumerate(zip(a,b)):
            if x != y:
                a = a[:i] + a[(i+1):]
                score -= 1
                return editingDistance(a,b)
            score -= 1
            a = a[:(len(a)-1)]
            return editingDistance(a,b)
    elif (len(a) < len(b)):
          for i, (x,y) in enumerate(zip (a, b)):
            if x != y:
                b = b[:i] + b[(i+1):]
                score -= 1
                return editingDistance(a,b)
          score -= 1
          b = b[:(len(b)-1)]
          return editingDistance(a,b)
    for i, (x,y) in enumerate(zip (a,b)):
      if x == y:
        score += 1
    return score
    
print(editingDistance('11011111','11'))
