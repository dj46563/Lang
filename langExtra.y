orop:       orop '||' orop      {  }
        |   andop               {  }
andop:      andop '&&' andop    {  }
        |   noteq               {  }

noteq:      noteq '!=' noteq    {  }
        |   comp                {  }

comp:       comp '>' comp       {  }
        |   comp '<' comp       {  }
        |   comp '<=' comp      {  }
        |   comp '>=' comp      {  }
        |   addit

