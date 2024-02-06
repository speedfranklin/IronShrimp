--
-- PostgreSQL database dump
--

-- Dumped from database version 16.1
-- Dumped by pg_dump version 16.1

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: datx; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.datx (
    filepath character varying(256) NOT NULL,
    filename character varying(128) NOT NULL,
    description character varying(1028),
    sampletype character varying(64),
    concentration double precision
);


ALTER TABLE public.datx OWNER TO postgres;

--
-- Name: datx datx_filename_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.datx
    ADD CONSTRAINT datx_filename_key UNIQUE (filename);


--
-- Name: datx datx_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.datx
    ADD CONSTRAINT datx_pkey PRIMARY KEY (filepath);


--
-- PostgreSQL database dump complete
--

