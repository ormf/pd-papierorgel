;;; 
;;; calc-bw.lisp
;;;
;;; **********************************************************************
;;; Copyright (c) 2024 Orm Finnendahl <orm.finnendahl@selma.hfmdk-frankfurt.de>
;;;
;;; Revision history: See git repository.
;;;
;;; This program is free software; you can redistribute it and/or
;;; modify it under the terms of the Gnu Public License, version 2 or
;;; later. See https://www.gnu.org/licenses/gpl-2.0.html for the text
;;; of this agreement.
;;; 
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;;; GNU General Public License for more details.
;;;
;;; **********************************************************************

(in-package :cl-user)

(defun q->bw (q)
  (/
   (log (+ (+ 1 (/ 1 (* 2 q q)))
           (sqrt (- (/ (expt (+ 2 (/ 1 (* q q))) 2) 4) 1)))
        10)
   (log 2 10)))

(q->bw 0.92)

(defun bw->q (bw)
  (let ((np2 (expt 2 bw)))
    (/
     (sqrt np2)
     (- np2 1))))



(defun omega (freq rate)
  (* 2 pi (/ freq rate)))

(defun alpha (freq bw &optional (rate 44100))
  (let ((omega (omega freq rate)))
    (* (sin omega)
       (sinh
        (* (/ (log 2) 2) ; => 0.3465736 (34.65736%)
           bw
           (/ omega (sin omega)))))))

(omega 1760 44100)

(alpha 1760 (* 0.01 14.4256) 44100)

(defun calc-bp-coeffs (freq bwo &optional (rate 44100))
  (let* ((omega (omega freq rate))
         (alpha (alpha freq (* 0.01 bwo) rate))
         (a0 (1+ alpha))
         (minus-a1 (* 2 (cos omega)))
         (minus-a2 (- alpha 1))
         (b0 alpha)
         (b1 0)
         (b2 (* -1 alpha)))
    (mapcar (lambda (x) (/ x 1))
            (list a0 minus-a1 minus-a2 b0 b1 b2))))

(calc-bp-coeffs 1760 14.4256)

(* 2 (cos (omega 1760 14.4256)))

(loop
  for (x y) on (mapcar #'bw->q
                       (loop
                         for partial from 1 to 16
                         collect (* 0.5 (log (/ (1+ partial) partial) 2))))
  while y collect (- y x))

'(1.41365 2.44926 3.464)

(defun bwtoq (bw)
  

  )

(defun qtobw)
