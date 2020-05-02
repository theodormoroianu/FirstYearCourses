-- Ex 1

-- first tree

SELECT titlu, valoare
FROM (SELECT o.cod_opera, o.titlu, o.valoare
      FROM (SELECT *
            FROM colectie
            WHERE proprietar='VV') c
      	    JOIN
      	    (SELECT *
      	     FROM opera
      	     WHERE cod_calerie='G1') o
      	    ON (c.opera=o.opera))
      	    
      INTERSECT
      
      (SELECT w.cod_opera, w.titlu, w.valoare
      FROM (SELECT cod_opera
            FROM restaureaza
            WHERE data>'15-JUN-2000') r
            JOIN
           (SELECT cod_opera, titlu, valoare
            FROM opera) w
           ON (w.cod_opera=r.cod_opera))
            
   
 
-- second tree

SELECT g.titlu, g.valoare
FROM (SELECT cod_opera
      FROM restaureaza
      WHERE data>'15-JUN-2000') r
      JOIN
      (SELECT o.cod_opera, o.titlu, o.valoare, o.cod_colectie
      FROM opera o JOIN colectie c on(o.cod_opera=c.cod_opera)
      WHERE cod_galerie='G1' AND c.proprietar='VV') g
      ON (r.cod_opera=g.cod_opera)
